# Image Similarity Lab

A C++20 research project for detecting exact, near, and transformed image
duplicates.

The project compares several approaches, including cryptographic hashes,
perceptual hashes, color and structural descriptors, local feature matching,
geometric verification, and similarity indexes.

The final system will support image-pair comparison and duplicate search
inside large collections. Each method will be evaluated by detection quality,
latency, throughput, memory usage, and robustness to compression, resizing,
cropping, rotation, color changes, watermarks, and other transformations.

The resulting repository will contain a reusable C++ library, command-line
tools, correctness tests, benchmarks, controlled datasets, experiment scripts,
performance graphs, and a reproducible technical report.
