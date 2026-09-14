# Next steps

Baseline: September 14, 2026. The repository records offline findings, with no verified vehicle port. Keep this plan tied to evidence rather than assuming LMC2 reception automatically permits steering.

## 1. Match the actual vehicle

**Input from the owner:** a read-only module-information export for the steering computer (PSCM), windshield camera (IPMA), and gateway (GWM), plus the adapter model and vehicle configuration. The [owner collection guide](OWNER_COLLECTION_GUIDE.md) explains how to collect it; the [worksheet](VEHICLE_INFO.md) provides a compact form. This input is not required to begin the next offline milestone.

**Result needed:** a comparison of installed hardware, strategy, and calibration identifiers against the public sample. A similar part-number prefix alone is insufficient. If the firmware differs, obtain a lawfully available matching sample and repeat the structural work before carrying addresses over.

This can happen alongside the next offline milestone.

## 2. Strengthen the decoding and trace steering permission

**Completed in the [post-validation follow-up](POST_VALIDATION_FINDINGS.md):** a narrow Ghidra store-width correction with 12 focused checks; LMC2 application getters and consumers; startup input-source selection with three exact-copy checks and four branch cases; status-summary bit 9 and two masks that require it; and the directory bank/override structure. These results do not complete the steering-permission trace.

**Work that can continue on a computer now:**

- Check the relevant V850 instruction semantics against authoritative processor documentation. The focused `st.w disp23` correction is verified, but other semantics and incomplete function prototypes still limit trust in decompiled C. Floating-point conversions and recovered arguments need particular care.
- Follow the new application paths: `0xED420` → `0xED884` → `0xED662`, and `0xF3E34` → the routines scheduled by `0xF3D2E`. Map the other bits required by the observed status masks and every subsequent enable/rejection condition. The sample's initialized LMC2 input selection is established; final steering permission is not.
- Trace arbitration with other steering functions, driver override, command bounds, fault handling, and the eventual authority applied to the steering actuator. Do not equate signal bit widths with actuator limits.
- Determine the actual runtime directory selection, including the separate RAM override that can replace receive-parameter slot 27. Identify the hardware counter's frequency: division by 8000 is established, but physical timeout units are not.

**Result needed:** an evidence table linking each relevant condition to its instructions, inputs, configured parameters, and still-unresolved dependencies. Any decoder correction should include a focused instruction check against the architecture definition. None of this requires a firmware patch or a vehicle connection.

## 3. Establish message delivery with passive evidence

**Input needed:** existing development captures, or carefully planned passive observations at the relevant network segments by someone equipped to do that work. A generic OBD connection does not automatically show the traffic at the steering rack. The adapter's model and capabilities must be established first.

**Result needed:** evidence that distinguishes a message present near the camera, absent after the gateway, and present at the steering computer. Record firmware/configuration identities, capture location, protocol, timing, and any observed faults with the data. A capture cannot establish acceptance solely because the message is visible.

Earlier developers reported gateway blocking and direct-rack network-termination trouble. Those are concrete issues to revisit with accurate topology and passive measurements; they are not proof that the steering application rejected correctly delivered requests.

## 4. Evaluate feasibility on a controlled bench

**Prerequisites:** a matched firmware analysis, an understood network setup, and an explicit description of the legitimate command and enable conditions. Decide with an experienced automotive-controls developer whether a representative bench setup is feasible.

**Result needed:** controlled observations separating receipt, validity, permission, timeout behavior, and rejection. Retain factory supervision and independent command limits. This milestone requires physical equipment and qualified engineering; static analysis cannot complete it.

A failure here should feed back into the documented hypothesis. Do not treat forcing an enable flag, disabling a watchdog, changing steering limits, or using a torque interceptor as confirmation of the factory-interface approach.

## 5. Create a focused implementation fork

Create an opendbc fork when a specific, supported-by-evidence change is ready. Add an openpilot fork only if integration changes require it.

The implementation would need accurate vehicle identification and geometry (including two-door versus four-door), a verified message path and controller, independent Panda enforcement, normal driver override/disengagement, and demonstrated fault handling. The intended initial control scope is lateral assistance with factory ACC retained, if the architecture allows it.

**Result needed before considering driving:** a reviewed implementation with meaningful safety-policy tests and appropriate bench/integration evidence. No installation or road-use release is currently scheduled.

## When the direction would change

If the matched steering firmware lacks a usable factory path, or the application requires defeating protections to use it, document that limitation. It is a valid research outcome. Conversely, an unexplained gateway failure or unknown enable condition alone does not establish that the platform is permanently locked down.

Public source updates and any owner-supplied Discord material can refine this plan. Preserve revision IDs and distinguish observed behavior, source-code interpretation, and hypotheses in each update.
