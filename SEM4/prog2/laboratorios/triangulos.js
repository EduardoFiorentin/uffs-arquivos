let str = prompt("Valores: ")
let values = str.split(" ")
let valuesFloat = []

values.forEach(element => {
    valuesFloat.push(parseFloat(element)) 
});

valuesFloat = valuesFloat.sort((a, b) => {
    if (a < b) return -1;
    else if (a > b) return 1
    else return 0

})

// se A ≥ B+C, apresente a mensagem: NAO FORMA TRIANGULO
// se A2 = B2 + C2, apresente a mensagem: TRIANGULO RETANGULO
// se A2 > B2 + C2, apresente a mensagem: TRIANGULO OBTUSANGULO
// se A2 < B2 + C2, apresente a mensagem: TRIANGULO ACUTANGULO
// se os três lados forem iguais, apresente a mensagem: TRIANGULO EQUILATERO
// se apenas dois dos lados forem iguais, apresente a mensagem: TRIANGULO ISOSCELES

let a = valuesFloat[2]
let b = valuesFloat[1]
let c = valuesFloat[0]

if     ( a >= (b + c) )                    console.log("NÃO FORMA TRIANGULO")
else {
    if     ( a*a == (b*b + c*c) )          console.log("TRIANGULO RETANGULO")
    if     (a*a > (b*b + c*c))             console.log("TRIANGULO OBTUSANGULO")
    if     (a*a < (b*b + c*c))             console.log("TRIANGULO ACUTANGULO")
    if     (a == b && b == c)              console.log("TRIANGULO EQUILATERO")
        
    if     ((a == b && a != c)||(a == c && a != b)||(b == c && b != a)) console.log("TRIANGULO ISOSCELES")
}

