# Bronco offline firmware investigation

Research date: 2026-09-14. Read the [firmware investigation](FIRMWARE_INVESTIGATION.md) first.

This repository contains offline analysis. No vehicle port is included. Scripts do not connect to an
OBD adapter, open a CAN interface, flash an ECU, or send steering commands.
Public firmware is downloaded only when you run the retrieval script. No raw
firmware or modified firmware is included in this repository.

## Reproduce the checks

Use Python 3.10 or newer from the repository root:

```bash
python3 fetch_firmware.py
python3 fetch_port_sources.py
python3 analyze_firmware.py
python3 check_checksum.py
```

Expected outcomes:

- Four pinned firmware-related files pass SHA-256 checks.
- Three VBFs yield six CRC-valid blocks.
- Two receive arrays contain 62 records each.
- LMC2 maps from CAN ID 0x3D6 to CAN-interface PDU 23, routing entry 31,
  destination index 53, and communications PDU 26.
- PDU 26 invokes receive callout 0x6AA00 and uses an eight-byte copy.
- Checksum comparison: 10,640 cases, zero mismatches.

The interpreter compares integer arithmetic in the included 0x74904 instruction
excerpt with the pinned upstream Python checksum function. It is not a complete
CPU emulator and does not validate steering or timing.

`results/firmware_structure.json` includes the disproved public table layout
under `published_interpretation_audit` for comparison. Use `receive_tables` and
`receive_routes` for the corrected findings. Do not use the retained old layout
as a dispatch map.

## Excerpts and Ghidra reproduction

The selected `.asm` and `.c` files are analysis excerpts from the public sample.
Function and data labels are generated. C prototypes, types, and some PCode
semantics are imperfect; C output must not be treated as compilable recovered
source. No exported file proves absence of a safety or activation condition.

The final analysis used official Ghidra 12.1.3 with JDK 21 and processor ID
`V850:LE:32:v850e3v5`. The official Ghidra release archive SHA-256 was:

```text
93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54
```

Ghidra source: https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.3_build

To create a project, replace the uppercase paths below with real absolute paths.
Create the project directory first. The `BroncoPrepare` script expects the VBF
extraction results to exist and applies the register values established from
startup, not the earlier guesses used during exploratory work.

```bash
GHIDRA/support/analyzeHeadless PROJECTS BroncoReview \
  -import REPO/results/NB3C-14D003-AB_block0_0x10040000.bin \
  -loader BinaryLoader -loader-baseAddr 0x40000 \
  -processor V850:LE:32:v850e3v5 \
  -scriptPath REPO/ghidra_scripts \
  -preScript BroncoPrepare.java REPO \
  -postScript BroncoDump.java REPO 84dcc,84d46,599c6,a41f0,a44aa,a4430,8fa06,6aa00,6aa16,74b76,747b4,74a1e,74904,74950,d0b34,d08ec,b77aa,b773c
```

Tool-generated names and function boundaries may change across analysis runs.
Basic instruction bytes and table values are the reproducibility targets.
One stock V850 `st.w disp23` PCode definition models a 16-bit store; this was
identified as a limitation rather than patched into an unreviewed firmware
simulation. The independent checksum interpreter uses only the basic operations
actually present in that routine. The research repository's processor patches
with broad placeholder decoders were not used for final excerpts.

## Files

- `firmware_download_manifest.json`: immutable firmware revision and expected hashes.
- `results/firmware_downloads_verified.json`: retrieval provenance for checked firmware files.
- `results/port_source_manifest.json`: URLs and hashes for the inspected source snapshots.
- `results/firmware_structure.json`: corrected tables, route details, calibration defaults,
  and integrity checks, plus the clearly marked superseded interpretation.
- `results/checksum_comparison.json`: checksum experiment result and exact excerpt hash.
- `results/ghidra/`: selected assembly and provisional decompiled C.
- `ghidra_scripts/`: analysis preparation, context, export, and indexing scripts.
- `results/INITIAL_BUNDLE_SHA256SUMS.json`: historical hashes for the original pre-repository archive and its original filenames; not a current repository manifest.

The Ghidra installation, JDK, pypcode installation, raw firmware, large exploratory
disassemblies, and abandoned processor experiments are excluded. The report
states which conclusions are established and which require more evidence.
