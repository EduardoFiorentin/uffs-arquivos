import { useState } from "react"

export default function Cadastro() {

    const [name, setName] = useState("")

    return (
        <form>
            <h2>Valor: {name}</h2>
            <input type="text" value={name} onChange={value => {
                setName(value.target.value)
            }} className="input"></input>
        </form>
    )
}