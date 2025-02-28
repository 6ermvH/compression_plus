# Compression Plus

Simple data compression project.

## Project Structure

```
compression_plus/
├── compressor/           # Main compression implementation
│   ├── src/              # Source code
│   ├── include/          # Header files
│   ├── data/             # Sample data for testing
│   ├── tests/            # Test suite
│   └── Makefile          # Build configuration
├── Report.pdf            # Technical documentation
└── README.md             # This file
```

## Build and Run

```bash
cd compressor
make
./compressor compress input_file output_file