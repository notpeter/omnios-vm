# Experimental OmniOS arm64

This branch adds the official **braich r151059** experimental image. It is not
an OmniOS stable or LTS release. The x86 default remains r151060; arm64 requires
an explicit release selection.

The image is built in `notpeter/omnios-builder` on branch `illumos_aarch64` from
<https://downloads.omnios.org/media/braich/>. The experimental package repository
is rolling, so installed package versions can be newer than the image snapshot.

The action temporarily applies `runtime/anyvm-0.7.7-braich.patch` to the pinned
anyvm 0.7.7 release asset, only for OmniOS arm64. Both the runtime and U-Boot
firmware are checked against SHA256 pins. Other architectures use the original
runtime. The patch selects U-Boot, MMIO virtio devices, and a generated device
tree with a serial alias instead of the generic EDK2/PCI configuration.

Validation targets Linux GitHub runners with QEMU TCG (including arm64 hosts).
The initial configuration uses 3072 MB RAM and two CPUs. Native acceleration,
other hosts, and NFS synchronization are not claimed supported. The advertised
sync methods are rsync, scp and tar.

The `Experimental arm64` workflow accepts an `omnios-builder` run ID, downloads
that run's image artifact, and tests the local action on x86 and arm64 runners.
It checks native C compilation and execution, environment forwarding,
synchronization in both directions, the persistent shell wrapper, and a
separate r151060 x86 regression job.

Image distribution and hosted validation are in progress; the experimental
builder version in the configuration is reserved for the validated artifact.

Local QEMU validation has passed boot, DHCP, SSH, DNS, GCC 14.3.0 native C
compilation/execution, SCP, rsync and tar round trips. Hosted action results are
still pending.
