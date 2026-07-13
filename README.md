# Image Similarity Lab

**Comparative research on exact, perceptual, geometric, and vector-based approaches to image duplicate detection.**

[Русская версия](README_RU.md)

`image-similarity-lab` is a research-oriented C++20 project for implementing, validating, benchmarking, and comparing multiple approaches to image duplicate and near-duplicate detection.

This repository is **not** intended to demonstrate one preferred hash or one fixed comparison pipeline. It is designed as an experimental framework for studying where different methods succeed, where they fail, and how they can be combined into an efficient cascade.

## Problem

Two files may represent the same visual content while having different byte representations because of recompression, resizing, format conversion, brightness changes, cropping, rotation, watermarking, or other transformations.

Therefore, duplicate detection must distinguish several cases:

- **exact duplicates** — identical file bytes;
- **near duplicates** — the same image after light transformations;
- **transformed duplicates** — the same visual content after crop, rotation, scale, or perspective changes;
- **semantic similarity** — different images with related content.

The project studies the trade-off between:

- **detection quality** — precision, recall, false positives, and false negatives;
- **robustness** — resistance to controlled image transformations;
- **performance** — extraction time, comparison time, throughput, and scalability;
- **memory cost** — bytes per image and index size;
- **system complexity** — preprocessing, indexing, and verification overhead.

## Research question

> How should exact hashes, perceptual hashes, local feature matching, and vector descriptors be combined to achieve a useful accuracy–latency–memory trade-off for near-duplicate image detection?

A longer-term objective is to evaluate cascaded pipelines in which inexpensive methods filter candidates before more expensive geometric or vector-based verification.

## Approaches under study

| Family | Planned approaches | Main purpose |
|---|---|---|
| Exact duplicate baseline | file size, SHA-256 | detect byte-identical files |
| Perceptual hashes | aHash, dHash, pHash, wHash | detect visually similar images after light transformations |
| Global descriptors | color and edge histograms | capture coarse visual structure |
| Local features | ORB, AKAZE, SIFT baselines | handle crop, rotation, scale, and partial overlap |
| Geometric verification | descriptor matching and RANSAC | reject accidental local-feature matches |
| Vector descriptors | learned image embeddings later | study stronger semantic and copy-detection baselines |
| Binary indices | brute force, BK-tree, multi-index hashing | accelerate Hamming-space search |
| Vector indices | exact search and ANN baselines later | scale embedding-based retrieval |
| Cascaded systems | cheap filtering followed by expensive verification | reduce average query cost while preserving recall |

No method is assumed to be universally best. The goal is to identify the transformation regimes and dataset conditions in which each approach belongs to the quality–performance Pareto frontier.

## Experimental workloads

The benchmark suite will contain original images, controlled positive transformations, and difficult negative pairs.

Planned transformations include:

- JPEG recompression;
- resize and format conversion;
- brightness and contrast changes;
- blur and noise;
- crop and borders;
- rotation and horizontal flip;
- watermarking;
- perspective distortion;
- combinations of several transformations.

Negative examples will include visually similar but non-duplicate images, repeated templates with different content, burst photos, similar scenes, and other hard negatives.

Dataset splits will be created by original-image identity so that transformed versions of the same source do not leak between validation and test sets.

## Evaluation metrics

### Detection quality

- true positives, false positives, false negatives, and true negatives;
- precision, recall, and F1-score;
- false-positive and false-negative rates;
- ROC and precision–recall curves where appropriate;
- recall@k for indexed retrieval;
- quality broken down by transformation type and severity.

### Performance

- image decoding time;
- preprocessing time;
- descriptor or hash extraction time;
- pair-comparison time;
- query latency and throughput;
- index construction time;
- scaling with collection size.

### Memory

- descriptor size per image;
- total index memory;
- temporary allocation cost;
- storage trade-offs for binary and floating-point descriptors.

## Experimental methodology

Experiments will separate:

- file I/O and decoding;
- image normalization;
- descriptor extraction;
- candidate retrieval;
- pair verification;
- metric calculation;
- CSV export and plotting.

Every report should record compiler and flags, CPU/GPU model, image dimensions, dataset version, transformation parameters, threshold-selection procedure, warm-up policy, repetitions, and summary statistics.

Thresholds will be selected on validation data and evaluated once on a separate test split.

## Roadmap

- [x] C++20 project infrastructure
- [x] initial Hamming-distance implementation and tests
- [ ] image decoding and normalized image representation
- [ ] grayscale conversion and resizing
- [ ] aHash implementation
- [ ] dHash implementation
- [ ] pair-comparison CLI
- [ ] Google Benchmark integration
- [ ] exact SHA-256 baseline
- [ ] pHash and frequency-domain experiments
- [ ] controlled transformation generator
- [ ] positive, negative, and hard-negative datasets
- [ ] threshold selection and quality metrics
- [ ] ORB-based feature matching
- [ ] RANSAC geometric verification
- [ ] directory scanning and brute-force retrieval
- [ ] BK-tree and other binary-hash indices
- [ ] cascaded detector evaluation
- [ ] learned descriptor and ANN baselines later

## Planned repository structure

```text
image-similarity-lab/
├── include/                 # public C++ interfaces
├── src/                     # algorithms and preprocessing
├── tests/                   # correctness and regression tests
├── benchmarks/              # extraction and search benchmarks
├── apps/                    # comparison and directory-scan tools
├── experiments/
│   ├── configs/             # reproducible experiment definitions
│   ├── results/             # generated CSV files
│   └── scripts/             # Python analysis and plotting
├── datasets/                # dataset documentation, not raw copyrighted data
└── reports/                 # tables, figures, and technical notes
```

## Current status

**Active development — production C++ foundation and first binary-similarity baseline.**

The current phase focuses on project infrastructure, tests, Hamming distance, and the first real-image hashing pipeline.

Neural embeddings, CUDA, ANN systems, and advanced geometric methods will be added only after exact and perceptual baselines are correct, benchmarked, and documented.

## Technology direction

- C++20;
- CMake;
- GoogleTest;
- Google Benchmark;
- sanitizers;
- a lightweight image decoder or OpenCV where justified;
- Python for result analysis and plotting;
- OpenMP or SIMD experiments later;
- GPU acceleration only after CPU baselines.

## License

This project is licensed under the MIT License.
