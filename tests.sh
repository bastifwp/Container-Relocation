seed=$1

#seeds=(121 255 11 123 501 135 108 268 151 326)
#seeds=(121)

# Directorios de input y output
instances_dir="Random_test"
output_dir="testing"

# Parámetros del algoritmo
max_gen=1000
popsize=40
pcross=0.6
pmut=0.4
pmut_swap=0.2
pmut_inversion=0.3
pmut_intFlip=0.5

mkdir -p "${output_dir}"

# Ciclo para cada instancia
for instance_path in "${instances_dir}"/*; do

  instance=$(basename "${instance_path}" .txt)
  output_file="${output_dir}/out_${instance}_${seed}.out"

  ./main "${instance_path}" "${seed}" "${max_gen}" "${popsize}" \
         "${pcross}" "${pmut}" "${pmut_swap}" "${pmut_inversion}" "${pmut_intFlip}" \
    > "${output_file}"

  echo "Generado: ${output_file}"
done