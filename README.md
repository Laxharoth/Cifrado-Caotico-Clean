# Spin-Wheel: A Fast and Secure Chaotic Encryption System with Data

This repository contains the research and implementation details for a novel chaotic encryption scheme designed for high security and extremely fast performance, particularly targeting real-time video communications. The scheme leverages a random roulette method for selecting and iterating through a graph of chaotic maps and a lookup table.

## Key Features

* **High Security:** Achieved through a unique combination of a chaotic map roulette, randomized trajectory selection from a lookup table, and the potential blending of trajectory segments from contiguous maps. This design ensures uniform distribution in map selection and trajectory generation, offering strong resistance against system and brute-force attacks.
* **Exceptional Speed:** The scheme demonstrates remarkably high encryption speeds (6 Gb/s), making it theoretically capable of supporting numerous real-time video communication streams without performance degradation.
* **Novel Random Trajectory Selection:** The random number generation involves three layers of randomization: chaotic map selection, trajectory selection within the map's lookup table, and a random offset within the chosen trajectory.
* **Resistance to Cryptanalytic Attacks:** Analysis suggests the scheme exhibits strong resistance against known ciphertext, known plaintext, and chosen ciphertext attacks. The uniform distribution of the ciphertext further hinders statistical analysis.
* **Integrity Check Mechanism:** The system includes a mechanism to verify the integrity of the information and detect modifications between encryption and decryption.

## Methodology

The CSPRN utilizes a graph of M chaotic maps and an NxM lookup table containing N pre-calculated trajectories for each map. The random number generation process involves:

1.  **Chaotic Map Spin-Wheel:** Randomly selecting one of the M chaotic maps.
2.  **Trajectory Selection:** Randomly choosing a trajectory from the selected map's column in the lookup table.
3.  **Offset Selection:** Randomly selecting a starting byte position (0-64) within the chosen 64-byte trajectory.

The generated pseudo-random numbers from this process are then used in a feedback-based block cipher for encryption. The encryption process can be described as:

$$
 C_{i}=E\left(P_{i}\right):=
    \begin{cases}
        \left(P_{i}+TF_{1,i}\right) \oplus TF_{2,i}\oplus \Phi_{M+1}\left(TF_{3,i}\right)           & \mid i=1 \\
        \left(P_{i}+TF_{1,i}\right) \oplus TF_{2,i}\oplus \Phi_{M+1}\left(C_{i-1} \oplus TF_{3,i}\right) & \mid i>1
    \end{cases}
$$

Where C is the ciphertext, E is the encryption function, P is the plaintextm, TF are the random numbers generated and \Phi is a deterministic transformatión.

## Results

Experimental analysis, including NIST randomness tests, demonstrates the robust randomness and uniform distribution of the generated sequences and map selections. Performance benchmarks show significantly faster encryption speeds compared to software implementations of AES. The sensitivity analysis to the encryption key also indicates high security against minor key variations.

## Integrity Check

The system incorporates an integrity check by concatenating a known byte sequence to the plaintext and encrypting it based on a hash of the plaintext. The decryption process verifies this overhead to ensure data integrity.

## Future Work

Potential future research directions include:

* In-depth security analysis against real-world attack scenarios.
* Performance comparisons with AES using hardware acceleration.
* Investigation of hardware implementations to further enhance speed.
* Analysis of parallelization potential.
