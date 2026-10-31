# theia-efi

EFI headers, linker scripts, and relocation code for [Theia](https://github.com/vcvtph2ps/theia).

The headers are derived from version 2.11 of the UEFI specification.

This project is intentionally minimal, it contains only what Theia and a few other projects needs to build and run as an EFI application. it may be expanded in future

Supported architectures: x86-64 and RISC-V 64.

## Building

Compile `src/relocate.c` and the architecture's entry file (`src/entry-x86_64.S` or `src/entry-riscv64.S`) into your application.

Then link with the matching linker script in `support/` using an ELF cross toolchain for the target.

The linker script produces a position independent image, so link as PIE with
4 KiB pages:

```sh
ld.lld -znoexecstack -pie -zcommon-page-size=0x1000 -zmax-page-size=0x1000
```

Finally, use `objcopy -O binary` to produce a flat binary and pad it up to a 4096 byte boundary.

## License

BSD 1-Clause. See [LICENSE](LICENSE) and [COPYING](COPYING).
