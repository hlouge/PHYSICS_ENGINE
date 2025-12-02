# Tutorial: Customizing the Fireworks Simulation

This tutorial will guide you through customizing the physics engine to create different visual effects. You will learn how to tweak physics parameters without coding, and how to modify the source code to change colors.

## Prerequisites

* You have compiled the project successfully (see `README.md`).
* You have the `Engine` executable in your `build/` directory.

---

## Part 1: Zero-Code Customization (Config File)

You can drastically change the behavior of the simulation just by editing the `config.txt` file located in your build directory.

### 1. The "Moon Gravity" Effect
Let's make the particles float longer, like they are on the Moon.

1.  Open `build/config.txt` in a text editor.
2.  Find the `GRAVITY` line.
3.  Change it from `9.81` to `1.62` (Moon gravity).

```ini
GRAVITY 1.62