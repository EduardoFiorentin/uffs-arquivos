let num_ent = parseInt(prompt("Numero de picos e vales: "))
let pcs_vls = prompt("picos e vales: ")

let list_pcs_vls = pcs_vls.split(" ")
let values_int = []

list_pcs_vls.map(value => values_int.push(parseInt(value)))

is_valid = true
let i = 1

while (i < num_ent - 1) {
    if (!((values_int[i-1] < values_int[i] && values_int[i+1] < values_int[i]) || (values_int[i-1] > values_int[i] && values_int[i+1] > values_int[i]))) {
        is_valid = false
        break
    }
    i++
}

if (is_valid) console.log(1)
else console.log(0)