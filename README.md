# zk-SNARK-libsnark

This example uses the libsnark library to define an R1CS (Rank-1 Constraint System) that represents a simple circuit, where the output is the product of two input values. It then generates a proof for this circuit using the ppzkSNARK proof system provided by libsnark, and verifies the proof using the same library.

Note that this is a simplified example and does not include error checking or handling of all possible edge cases. It is also important to use secure random number generation when generating secret keys and other sensitive data.
