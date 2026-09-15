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

The owner-supplied As-Built record is a private input. Only selected non-unique module part/software identifiers and original explanatory analysis are published; VINs, serials, manufacturing codes, raw configuration data, and the source filename/hash are excluded. [Identification findings](docs/ASBUILT_FINDINGS.md). The comparison uses the Ford firmware-response database in upstream opendbc at the existing `057aee25...` pin; its hash and the extracted Ranger EPS identifier list are in [the comparison record](results/owner_asbuilt_comparison.json).

Additional camera, F-150 steering, and Transit Custom diagnostic-reference files use the same pinned `ghostdev137/ford-pscm-re` revision. Their hashes and paths appear in [module_firmware_manifest.json](module_firmware_manifest.json), with derived structure/checksum results in [the module inventory](results/module_firmware_inventory.json). These comparison materials are not matched to the owner's installed modules. The gateway MDX is a diagnostic definition, not executable code.

The gateway search consulted [incognitojam/op-notebooks at revision 1109fbdb](https://github.com/incognitojam/op-notebooks/tree/1109fbdb25e3bdb7bfb7033a56bba7338bb60688), specifically its download workflow and historical VBF inventory. The documented Ford endpoint returned server-error content on both attempts; no firmware was obtained there. Its separate As-Built script was inspected but not run, and its embedded session/CAPTCHA values were not used. See [acquisition findings](docs/FIRMWARE_ACQUISITION.md).

The follow-up also uses the [Renesas-authored RH850G3M software manual](https://docs.alexrp.com/v850/rh850g3m.pdf), R01US0123EJ0140 Rev.1.40, pages 314, 386, and 392. That copy is hosted on a third-party mirror. Its instruction definitions do not identify the Bronco's exact processor model. The narrow Ghidra language correction and hashes are documented in [the follow-up report](docs/POST_VALIDATION_FINDINGS.md).

## Development history

- [AJ/ajzride's posts in the Bronco6G development discussion](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-29) describe earlier decompilation, legacy-CAN/CAN-FD differences, gateway delivery observations, and direct-rack harness/termination difficulties. See especially the May 15 and June 27, 2026 posts. These are firsthand development reports, not observations from the target vehicle.
- [The following thread page](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-30) was reviewed for follow-up context.
- [JimDiesel's Garage: Bronco OpenPilot Test Build](https://www.youtube.com/watch?v=PpQoKbeA-WM), August 5, 2024, is historical context. Video playback was not analyzed; no technical result here depends on what it demonstrates.
- [comma's safety documentation](https://docs.comma.ai/concepts/safety/) describes the intended independent safety architecture.

No private Discord channels were accessed. No community member was contacted. The corrected table interpretation and receiver trace are independent results, not a claim of priority over unpublished work. Listing sources does not imply endorsement of this project by their authors, Ford, or comma.

## Licensing scope

The README banner combines a supplied Bronco illustration, generated background graphics, and Rubik Black lettering. See [artwork provenance and font licensing](assets/README.md). The MIT grant below does not relicense the supplied illustration or third-party branding.

The MIT license in this repository applies to original analysis scripts, Ghidra helper scripts, and original explanatory text. It does not grant rights to third-party firmware, downloaded dependencies/source, or firmware-derived material.

`results/ghidra/` and `results/followup/ghidra/` contain selected disassembly and provisional decompilation excerpts derived from the public firmware sample. They are identified as third-party-derived research material, not original Ford source or material relicensed under MIT. Embedded firmware header text in the structured results is also third-party material. All third-party rights and any applicable upstream terms remain with their respective owners. No raw or modified firmware is distributed here.

The original archive's hash list is preserved as [INITIAL_BUNDLE_SHA256SUMS.json](results/INITIAL_BUNDLE_SHA256SUMS.json). It describes the pre-repository bundle, including its original filenames; it is historical provenance, not a checksum manifest for the current repository. Repository commits track subsequent edits.
