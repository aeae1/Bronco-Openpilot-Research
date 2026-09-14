# README artwork

The selected design is layout B with font choice 6, **Rubik Black**.

- `readme-banner.png` is the README display asset, 2170 × 828 pixels.
- `readme-banner.svg` is the self-contained composition source. Its visible headline is outlined, so it does not require an installed font.
- The supplied Bronco JPEG is embedded at its original 1448 × 1086 dimensions and positioned with uniform scaling. The visible vehicle uses a single scale factor, `520 / 1448`; there is no separate horizontal or vertical stretching.
- The off-white/sage background and road graphics were generated with OpenAI image generation. The final composition combines that background with the supplied illustration and selected vector lettering.

Rubik is credited to **The Rubik Project Authors** and distributed under the SIL Open Font License 1.1. See [the accompanying font license](licenses/Rubik-OFL.txt) and [the upstream font folder](https://github.com/google/fonts/tree/main/ofl/rubik). The source `Rubik[wght].ttf` used for the headline had Git blob SHA `a59aeb632df494345a542697c357f608875481b0`; weight 900 was used without slanting or nonuniform scaling.

To export with Inkscape:

```bash
inkscape assets/readme-banner.svg --export-type=png --export-filename=assets/readme-banner.png --export-width=2170
```

The repository's software/text MIT license does not grant rights to the supplied vehicle illustration or third-party branding. No additional rights in that supplied artwork are asserted here. These visuals do not imply endorsement by Ford or comma.
