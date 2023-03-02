#include <iostream>
#include <cstdlib>
#include <vector>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>

using namespace std;
using namespace libsnark;

int main(int argc, char** argv) {
    // Initialize the ppzkSNARK proof system
    default_r1cs_ppzksnark_pp::init_public_params();

    // Define the R1CS (Rank-1 Constraint System) that the proof system will operate on
    const size_t num_constraints = 2;
    const size_t input_size = 2;
    r1cs_constraint_system<FieldT> cs;
    cs.primary_input_size = input_size;
    cs.auxiliary_input_size = 0;

    // Add constraints to the R1CS
    // In this example, we'll use the simple circuit x1 * x2 = out
    variable<FieldT> x1, x2, out;
    x1.allocate(cs);
    x2.allocate(cs);
    out.allocate(cs);
    cs.add_constraint(x1 * x2 == out);

    // Create the witness to the R1CS
    // In this example, we'll use the inputs x1=2 and x2=3
    const vector<FieldT> primary_input = {2, 3};
    const vector<FieldT> auxiliary_input = {};
    r1cs_primary_input<FieldT> witness(primary_input);

    // Generate the proof
    r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof =
        r1cs_ppzksnark_prover<default_r1cs_ppzksnark_pp>(cs, witness, auxiliary_input);

    // Verify the proof
    bool verified = r1cs_ppzksnark_verifier_strong_IC<default_r1cs_ppzksnark_pp>(cs, proof, primary_input);
    if (verified) {
        cout << "Proof verified!" << endl;
    } else {
        cout << "Proof not verified." << endl;
    }

    return 0;
}
