# BluePilot research relevant to the Bronco investigation

Reviewed September 15, 2026, after the owner supplied the January article. These are external developer reports and research leads, separate from this repository's binary checks. No vehicle operation, firmware modification, or change to independent safety checks is proposed here.

## January signal-limit experiments

BluePilot reports that steering response depends on speed, the combination of path signals, and which safety limits apply. Its low-speed measurements used Mach-E/F-150 vehicles with comma safety limits disabled. The post also describes unwanted steering persistence under strong commands. These measurements do not establish the Bronco's operating limits or demonstrate safe assistance. [January 7 article and measurement chart](https://bluepilot.dev/2026/01/07/what-exactly-are-the-limits-of-ford-lane-assist-signals/).

For this project, the useful question is how valid path inputs become steering requests and interact over time. Signal encoding ranges alone cannot answer that question. Retaining the physical steering controller does not by itself validate an external controller's complete behavior.

## July firmware-analysis report

BluePilot later reports using Ford VBF files to investigate a speed-dependent curvature filter and delayed response on CAN-FD Ford platforms. It proposes a different mix of native path inputs and states that Ford and comma limits remain applicable. The article gives a program address and numerical timing claims without binding them to an exact executable hash. Treat these as leads for verification, not measurements of the owner's firmware. [July 15 technical post](https://bluepilot.dev/2026/07/15/bluepilot-7-0-the-return-of-angle-control-it-wasnt-the-models-fault/).

The [July 17 release announcement](https://bluepilot.dev/2026/07/17/bluepilot-7-0-is-now-live/) says version 7.0 was released. A release announcement does not establish full-size Bronco compatibility or a reviewed safety implementation.

Before relying on this direction:

1. Identify the exact source-code revision, executable, calibration set, and processor/address mapping behind each relevant claim.
2. Inspect the controller implementation and independent Panda checks together. A statement that limits remain is not an audit of how the new inputs are bounded or combined.
3. Trace the relevant input consumers and state updates in matching firmware. Separate evidence of a filter from evidence of how that filter affects a complete closed-loop controller.
4. If a routine can be emulated, document all supplied inputs, timing assumptions, and omitted hardware dependencies. A passing isolated routine is not a full vehicle validation.

These steps refine the existing [steering-permission research](NEXT_STEPS.md#2-strengthen-the-decoding-and-trace-steering-permission); they do not justify downloading an installer onto the owner's comma device or changing vehicle configuration.

## Connection to the firmware source already used

BluePilot's April post links `ghostdev137/ford-pscm-re`, the repository supplying this project's existing comparison samples. It describes timeout/minimum-speed modifications demonstrated on a Transit, a direction outside this project's retained-protection boundary. The shared source also means these reports should not automatically be counted as independent confirmation. [April 27 progress post](https://bluepilot.dev/2026/04/27/ford-lka-openpilot-progress/).

The post's wording about extracting firmware through FORScan does not establish a verified read-back procedure for this Bronco. It is not a reason to request a dump or start a programming session with the owner's adapter.

## What this changes for the owner

The reports make BluePilot a more specifically motivated firmware-source lead: its authors may know where relevant original steering packages came from. Neither article supplies the missing `MB3T-14H483-FAH` gateway executable or establishes that the authors have it. No contact was made.

The owner's [FORScan identifiers](FORSCAN_FINDINGS.md) remain the basis for acquisition. Its reported `RB3C-14D003-AA` steering strategy differs from this repository's analyzed sample. The January and July steering-response reports also do not resolve delivery between the camera and steering network groups. Those remain separate questions requiring separate evidence.
