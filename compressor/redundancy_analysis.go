package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"os/exec"
	"path/filepath"
	"sync"
	"time"
)

func entropy(probabilities []float64) float64 {
	var h float64
	for _, p := range probabilities {
		if p > 0 {
			h -= p * math.Log2(p)
		}
	}
	return h
}

func gallagerBound(probabilities []float64) float64 {
	pMax := 0.0
	for _, p := range probabilities {
		if p > pMax {
			pMax = p
		}
	}
	
	h := entropy(probabilities)
	return h + pMax - 1 + math.Log2(math.E)/math.E
}

func generateTestFile(filename string, p1 float64, fileSize int) error {
	fmt.Printf("Generating file %s (p1=%.1f, size=%d)...\n", filename, p1, fileSize)
	
	content := make([]byte, fileSize)
	for i := 0; i < fileSize; i++ {
		if rand.Float64() < p1 {
			content[i] = 'A'
		} else {
			content[i] = 'B'
		}
	}
	
	os.MkdirAll(filepath.Dir(filename), 0755)
	return os.WriteFile(filename, content, 0644)
}

func compressFile(inputFile, outputFile string) error {
	fmt.Printf("Compressing %s to %s...\n", inputFile, outputFile)
	
	os.MkdirAll(filepath.Dir(outputFile), 0755)
	
	cmd := exec.Command("./main", inputFile, outputFile)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("compression error: %v\nOutput: %s", err, output)
	}
	
	return nil
}

func calculateRedundancy(p1 float64, fileSize int, expNum int, sessionId string) (float64, float64, error) {
	dataDir := "data"
	os.MkdirAll(dataDir, 0755)
	
	inputFile := filepath.Join(dataDir, fmt.Sprintf("test_p%.1f_%s_%d.txt", p1, sessionId, expNum))
	outputFile := filepath.Join(dataDir, fmt.Sprintf("test_p%.1f_%s_%d.huff", p1, sessionId, expNum))
	
	if err := generateTestFile(inputFile, p1, fileSize); err != nil {
		return 0, 0, err
	}
	
	if err := compressFile(inputFile, outputFile); err != nil {
		return 0, 0, err
	}
	
	inputInfo, _ := os.Stat(inputFile)
	outputInfo, _ := os.Stat(outputFile)
	
	probabilities := []float64{p1, 1.0 - p1}
	entropyVal := entropy(probabilities)
	actualBitsPerSymbol := float64(outputInfo.Size()*8) / float64(inputInfo.Size())
	redundancy := actualBitsPerSymbol - entropyVal
	gallagerVal := gallagerBound(probabilities)
	
	fmt.Printf("Exp p1=%.1f #%d: entropy=%.6f, actual=%.6f, redundancy=%.6f, gallager=%.6f\n",
		p1, expNum, entropyVal, actualBitsPerSymbol, redundancy, gallagerVal)
	
	return redundancy, gallagerVal, nil
}

func main() {
	sessionId := fmt.Sprintf("%d", time.Now().UnixNano())
	rand.Seed(time.Now().UnixNano())
	
	fileSize := 5000
	experiments := 5
	
	resultsFile, _ := os.Create(fmt.Sprintf("results_%s.csv", sessionId))
	defer resultsFile.Close()
	
	resultsFile.WriteString("p1,Redundancy,GallagerBound\n")
	
	fmt.Println("Starting Huffman code redundancy analysis...")
	fmt.Printf("Session ID: %s, %d experiments, filesize: %d bytes\n", sessionId, experiments, fileSize)
	
	var wg sync.WaitGroup
	resultsChan := make(chan string, experiments*9)
	
	os.MkdirAll("data", 0755)
	
	for p1 := 0.1; p1 <= 0.9; p1 += 0.1 {
		p1Fixed := math.Round(p1*10) / 10
		
		for exp := 1; exp <= experiments; exp++ {
			wg.Add(1)
			go func(p1 float64, expNum int) {
				defer wg.Done()
				
				redundancy, gallagerBound, err := calculateRedundancy(p1, fileSize, expNum, sessionId)
				if err != nil {
					fmt.Printf("Error for p1=%.1f, exp=%d: %v\n", p1, expNum, err)
					return
				}
				
				result := fmt.Sprintf("%.1f,%.6f,%.6f", p1, redundancy, gallagerBound)
				resultsChan <- result
				resultsFile.WriteString(result + "\n")
			}(p1Fixed, exp)
		}
	}
	
	go func() {
		wg.Wait()
		close(resultsChan)
	}()
	
	results := make(map[float64]struct {
		rSum, gSum float64
		count int
	})
	
	for result := range resultsChan {
		var p1, r, g float64
		fmt.Sscanf(result, "%f,%f,%f", &p1, &r, &g)
		
		p1 = math.Round(p1*10) / 10
		data := results[p1]
		data.rSum += r
		data.gSum += g
		data.count++
		results[p1] = data
	}
	
	summaryFile, _ := os.Create(fmt.Sprintf("summary_%s.csv", sessionId))
	defer summaryFile.Close()
	
	summaryFile.WriteString("p1,AvgRedundancy,AvgGallagerBound,Difference\n")
	
	fmt.Println("\nAverages:")
	fmt.Println("p1,AvgRedundancy,AvgGallagerBound,Difference")
	
	for p1 := 0.1; p1 <= 0.9; p1 += 0.1 {
		p1 = math.Round(p1*10) / 10
		if r, ok := results[p1]; ok && r.count > 0 {
			avgR := r.rSum / float64(r.count)
			avgG := r.gSum / float64(r.count)
			diff := avgR - avgG
			
			line := fmt.Sprintf("%.1f,%.6f,%.6f,%.6f\n", p1, avgR, avgG, diff)
			summaryFile.WriteString(line)
			fmt.Print(line)
		}
	}
	
	fmt.Println("\nАнализ завершен!")
	fmt.Printf("Результаты: results_%s.csv\n", sessionId)
	fmt.Printf("Сводка: summary_%s.csv\n", sessionId)
}
