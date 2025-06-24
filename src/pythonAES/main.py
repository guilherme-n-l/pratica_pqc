from os import urandom
from os.path import abspath, join
from subprocess import run

print("Alice will now create her key pair...")
alice_1_path = "../../build/alice_kem"
print(run([alice_1_path]).stdout)

print("Heres Bob creating a key to be exchanged...")

KEY_SIZE_BITS = 256

key = urandom(KEY_SIZE_BITS // 8)

print("Generated Key: ", key.hex())

key_file = abspath("key.hex")
print("Saving Key to file: ", key_file)

with open(key_file, "w") as f:
    f.write(key.hex())
    f.close()
    print("Saved Key successfully")

print("Bob will ecapsulate key...")
bob_path = "../../build/bob_kem"
run([bob_path]).stdout

print("Alice will now decapsulate key...")
alice_2_path = "../../build/alice2_kem"
run([alice_2_path]).stdout
