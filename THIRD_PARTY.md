# Provenance and credits

Initial research date: September 14, 2026. Prepared with ChatGPT/Codex for the repository owner. All reported experiments were performed on local files; no vehicle test or firmware write was performed.

## Public source snapshots

| Source | Pinned revision / role |
|---|---|
| [ghostdev137/ford-pscm-re](https://github.com/ghostdev137/ford-pscm-re/tree/f545afe509aa936a32ad026d411add394f8464ae) | `f545afe509aa936a32ad026d411add394f8464ae`: public Bronco firmware sample and prior reverse engineering |
| [commaai/opendbc](https://github.com/commaai/opendbc/tree/057aee25b5eee7530f0b95b5b508c8c3247b0cd7) | `057aee25b5eee7530f0b95b5b508c8c3247b0cd7`: Ford message definitions, checksum, vehicle definitions, and safety code |
| [mims002/opendbc](https://github.com/mims002/opendbc/tree/690bcf4a60d22a445e007a7766a0914d9739b8ef) | `690bcf4a60d22a445e007a7766a0914d9739b8ef`: experimental Bronco code inspected for comparison |
| [Official Ghidra 12.1.3](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.3_build) | Analysis tool; final processor selection `V850:LE:32:v850e3v5` |

Individual file hashes and URLs are recorded in [firmware_download_manifest.json](firmware_download_manifest.json), [the source manifest](results/port_source_manifest.json), and [verified firmware retrieval results](results/firmware_downloads_verified.json).

Raw firmware and retrieved third-party source are downloaded on demand and ignored by git. Availability at a public URL does not authenticate firmware as a Ford-approved release or establish compatibility with the target vehicle.

## Development history

- [AJ/ajzride's posts in the Bronco6G development discussion](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-29) describe earlier decompilation, legacy-CAN/CAN-FD differences, gateway delivery observations, and direct-rack harness/termination difficulties. See especially the May 15 and June 27, 2026 posts. These are firsthand development reports, not observations from the target vehicle.
- [The following thread page](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-30) was reviewed for follow-up context.
- [JimDiesel's Garage: Bronco OpenPilot Test Build](https://www.youtube.com/watch?v=PpQoKbeA-WM), August 5, 2024, is historical context. Video playback was not analyzed; no technical result here depends on what it demonstrates.
- [comma's safety documentation](https://docs.comma.ai/concepts/safety/) describes the intended independent safety architecture.

No private Discord channels were accessed. No community member was contacted. The corrected table interpretation and receiver trace are independent results, not a claim of priority over unpublished work. Listing sources does not imply endorsement of this project by their authors, Ford, or comma.

## Licensing scope

The README banner combines a supplied Bronco illustration, generated background graphics, and Rubik Black lettering. See [artwork provenance and font licensing](assets/README.md). The MIT grant below does not relicense the supplied illustration or third-party branding.

The MIT license in this repository applies to original analysis scripts, Ghidra helper scripts, and original explanatory text. It does not grant rights to third-party firmware, downloaded dependencies/source, or firmware-derived material.

`results/ghidra/*.asm` and `results/ghidra/*.c` are selected disassembly and provisional decompilation excerpts derived from the public firmware sample. They are identified as third-party-derived research material, not original Ford source or material relicensed under MIT. Embedded firmware header text in the structured results is also third-party material. All third-party rights and any applicable upstream terms remain with their respective owners. No raw or modified firmware is distributed here.

The original archive's hash list is preserved as [INITIAL_BUNDLE_SHA256SUMS.json](results/INITIAL_BUNDLE_SHA256SUMS.json). It describes the pre-repository bundle, including its original filenames; it is historical provenance, not a checksum manifest for the current repository. Repository commits track subsequent edits.
