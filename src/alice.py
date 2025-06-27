from kyber_py.ml_kem import ML_KEM_512

print("Alice will now create her key pair...")
aek, adk = ML_KEM_512.keygen()
print("Alice: Private key:", aek.hex())
print("Alice: Public key:", adk.hex())
