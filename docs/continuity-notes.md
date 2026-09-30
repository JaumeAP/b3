# Continuity notes

## Evergreen state

1. The repository is an empty monorepo skeleton: `apps/` and `packages/` hold only `.gitkeep`; there is no code yet.
2. `.claude/skills/` vendors three project skills: `response-style`, `git-sync-and-merge`, `continuity-notes-rules`.
3. Open thread: what a Pro Tools integration would need. The goal mentioned is a monitoring EQ on the final output, which Pro Tools cannot insert on physical HDX outputs.
4. Candidate approaches for that EQ, all unverified against Avid documentation: a Master Fader on the monitor output path, a separate monitor path fed from a mix bus (so bounces stay clean), or a hardware insert in I/O Setup.
5. Unverified points still to check: AudioSuite-specific requirements, whether recent Pro Tools versions offer post-fader inserts, and the maximum Master Fader channel width per edition.

## Previous session

1. Described the repository contents (skeleton only).
2. Researched Pro Tools extension points via web search results only (no official Avid pages opened): AAX real-time plug-ins, AudioSuite, and the PTSL scripting SDK.
3. Registration with Avid, an iLok account and PACE signing for commercial AAX are required; PTSL is gRPC on `localhost:31416`.
4. Answered follow-ups about pre/post-fader inserts, output-stage EQ and Master Fader width from memory, flagged as unverified.
