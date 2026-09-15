# Next steps

Baseline: September 14, 2026; updated September 15 with [read-only Discord findings](DISCORD_FORD_REVIEW.md). The repository records offline findings, with no verified vehicle port. Keep this plan tied to evidence rather than assuming LMC2 reception automatically permits steering.

## 1. Match the actual vehicle

**Progress September 15:** the owner's As-Built record identifies all three target modules. Its steering program and both relevant data identifiers differ from the analyzed sample. [Comparison](ASBUILT_FINDINGS.md). The [exact file request](FIRMWARE_FILE_REQUEST.md) prioritizes the gateway, then the recorded steering set, then the camera set. No matching executable firmware was obtained. The owner has now supplied connected-session FORScan identification matching the three main strategies, all three displayed part numbers, and two displayed calibration identifiers. [Findings and limits](FORSCAN_FINDINGS.md).

**Owner identification received:** Configuration text, Log/Modules screenshots, FORScan 2.3.68 on Windows, and the OHP USB ELM327 adapter model. No repeat identification collection is needed for this step. The [owner collection guide](OWNER_COLLECTION_GUIDE.md) and [worksheet](VEHICLE_INFO.md) remain available for future collections.

**Identification result:** the reported steering strategy and displayed calibration differ from the public sample. **Remaining work:** obtain matching executable/data files and repeat the structural work before carrying addresses over. A similar part-number prefix or a diagnostic identifier alone cannot establish binary equivalence.

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

**Input needed:** existing development captures, or carefully planned passive observations at the relevant network segments by someone equipped to do that work. A generic OBD connection does not automatically show the traffic at the steering rack. The owner's OHP ELM327 adapter has been identified, but its successful diagnostic read does not establish passive capture capability on the relevant segments.

**Result needed:** evidence that distinguishes a message present near the camera, absent after the gateway, and present at the steering computer. Record firmware/configuration identities, capture location, protocol, timing, and any observed faults with the data. A capture cannot establish acceptance solely because the message is visible.

The [January 2024 Discord context](DISCORD_FORD_REVIEW.md#what-the-earlier-attempts-demonstrated) adds bus reassignment and a stale-send error. February reports describe LMC1 crossing the gateway and direct-bus LMC2 attempts; the original tester's May 2026 follow-up adds uncertainty about improvised wiring. These reports do not establish that correctly delivered LMC2 was rejected by the steering application. The previously documented June 27 gateway-blocking and termination report remains relevant. Later custom-harness proposals do not supply a validated gateway solution.

**Immediate offline task:** reconstruct the earlier software profile, transmit bus, Panda policy/build, send timestamps, and physical receive evidence from existing shareable material. Separate routing, stale transmission, LKA availability loss, wakeup, and steering permission. No successful Bronco-specific keepalive fix was established by the inspected discussion. Preserve freshness and watchdog checks while investigating their inputs.

## 4. Evaluate feasibility on a controlled bench

**Prerequisites:** a matched firmware analysis, an understood network setup, and an explicit description of the legitimate command and enable conditions. Decide with an experienced automotive-controls developer whether a representative bench setup is feasible.

**Result needed:** controlled observations separating receipt, validity, permission, timeout behavior, and rejection. Retain factory supervision and independent command limits. This milestone requires physical equipment and qualified engineering; static analysis cannot complete it.

A failure here should feed back into the documented hypothesis. Do not treat forcing an enable flag, disabling a watchdog, changing steering limits, or using a torque interceptor as confirmation of the factory-interface approach.

## 5. Create a focused implementation fork

Create an opendbc fork when a specific, supported-by-evidence change is ready. Add an openpilot fork only if integration changes require it.

The implementation would need accurate vehicle identification and geometry (including two-door versus four-door), a verified message path and controller, independent Panda enforcement, normal driver override/disengagement, and demonstrated fault handling. The intended initial control scope is lateral assistance with factory ACC retained, if the architecture allows it.

**Result needed before considering driving:** a reviewed implementation with meaningful safety-policy tests and appropriate bench/integration evidence. The [existing BluePilot control-permission finding](BLUEPILOT_SITE_REVIEW.md#independent-safety-code-check) remains a separate unresolved gate; the inspected development revision was unchanged in this follow-up. Tie any proposed implementation to its actual Panda build and verify controls-disabled, reset, stale-input, disengagement, and driver-override behavior. No installation or road-use release is currently scheduled.

## When the direction would change

If the matched steering firmware lacks a usable factory path, or the application requires defeating protections to use it, document that limitation. It is a valid research outcome. Conversely, an unexplained gateway failure or unknown enable condition alone does not establish that the platform is permanently locked down.

Public source updates and further authorized, read-only Discord review can refine this plan. Preserve revision IDs and distinguish observed behavior, source-code interpretation, and hypotheses in each update.
