# Image Similarity Lab

## Core idea

A CPU-first C++20 lab for finding visually similar and near-duplicate images using perceptual hashes, Hamming distance, indexing structures, benchmarks, and performance experiments.

## Main question

Which simple image similarity methods provide the best trade-off between robustness, query speed, memory usage, and implementation complexity?

## Why this project

This project combines:
- C++ production structure
- algorithms and data structures
- CPU performance experiments
- benchmarks and profiling
- visual results
- future GPU acceleration path

## Initial algorithms

- average hash / aHash
- difference hash / dHash
- Hamming distance
- brute-force top-k search
- BK-tree later
- LSH buckets later
- DSU clustering later

## Initial data structures

- uint64_t image hashes
- vector of image entries
- priority_queue for top-k
- unordered_map for buckets later
- BK-tree later
- DSU for duplicate groups later

## CPU performance angle

- std::popcount for Hamming distance
- millions of uint64_t comparisons
- AoS vs SoA layout
- query latency
- comparisons per second
- cache behavior later with perf

## Future GPU angle

- batch Hamming distance on CUDA
- parallel hash computation
- GPU brute-force reranking

## First milestone

Synthetic hash benchmark:
- implement hamming_distance(uint64_t, uint64_t)
- implement brute-force top-k over synthetic hashes
- test correctness
- benchmark comparisons/sec

## What not to do yet

- no neural networks
- no CLIP
- no OpenCV
- no GUI
- no web app
- no database
- no CUDA at the beginning
