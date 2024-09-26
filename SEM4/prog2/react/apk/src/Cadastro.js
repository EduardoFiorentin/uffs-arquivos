import { useState } from "react"

export default function Cadastro() {

    const [name, setName] = useState("")

    return (
        <form>
            <input type="text" value={name} onChange={value => {
                setName(value.target.value)
            }} className="input"></input>
        </form>
    )
}