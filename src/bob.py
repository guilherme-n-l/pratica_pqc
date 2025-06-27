import os
import sys
from kyber_py.ml_kem import ML_KEM_512


def gen():
    private_key_file = "bob_private.bin"
    public_key_file = "bob_public.bin"

    if os.path.exists(private_key_file) and os.path.exists(public_key_file):
        print("Keys found! Loading the keys...")
        with open(private_key_file, "rb") as f:
            bdk = f.read()
        with open(public_key_file, "rb") as f:
            bek = f.read()
    else:
        print("Keys not found! Generating a new key pair...")

        bek, bdk = ML_KEM_512.keygen()

        with open(private_key_file, "wb") as f:
            f.write(bdk)
        with open(public_key_file, "wb") as f:
            f.write(bek)

    print(
        f"Bob: Private key ({len(bdk)} bytes):", bdk.hex()[:20], "...", bdk.hex()[-5:]
    )
    print(f"Bob: Public key ({len(bek)} bytes):", bek.hex()[:20], "...", bek.hex()[-5:])


def gen_key():
    alice_public_key_file = "alice_public.bin"
    with open(alice_public_key_file, "rb") as f:
        aek = f.read()
    key, ct = ML_KEM_512.encaps(aek)
    print(
        f"Bob: Generated key ({len(key)} bytes):",
        key.hex()[:20],
        "...",
        key.hex()[-5:],
    )
    print(
        f"Bob: Generated cypher ({len(ct)} bytes):",
        ct.hex()[:20],
        "...",
        ct.hex()[-5:],
    )

    ct_file = "key.bin"
    with open(ct_file, "wb") as f:
        f.write(ct)

    key_file = "key.hex"
    with open(key_file, "w") as f:
        f.write(key.hex())


def main():
    if len(sys.argv) < 2:
        print("Usage: python bob.py <command>")
        sys.exit(1)

    command = sys.argv[1]

    if command == "gen":
        gen()
    elif command == "gen_key":
        gen_key()
    else:
        print(f"Unknown command: {command}")
        print("Available commands: gen, get_private, get_public")
        sys.exit(1)


if __name__ == "__main__":
    main()
