import express from 'express'
// import router from "./routes"
import pgPromise from 'pg-promise'
import cors from "cors"


const server = express()
const PORT = 3000
const pgp = pgPromise({})


// const user = "progII"
// const pass = "uffs"
// const host = "host"
// const port = "Port"
// const db_name = "database name"

// const db = pgp(`postgres://${user}:${pass}@192.168.253.155:5432/progII`)
// 
const usuario = "prog"; 
const senha = "uffs";
const db = pgp(`postgres://${usuario}:${senha}@172.20.66.230:5432/prog`);

server.use(express.json())
server.use(cors())

// server.use(router)


server.get("/aluno", async (req, res) => {
    try {
        // const alunos = await db.many("SELECT * FROM aluno;")
        // res.status(200).json(alunos)
        res.status(200).json([
            {
                nome: "Eduardo",
                matricula: "2211100002", 
                curso: "Ciência da Computação"
            },
            {
                nome: "B",
                matricula: "2211100002", 
                curso: "Ciência da Computação"
            },
            {
                nome: "C",
                matricula: "2211100002", 
                curso: "Ciência da Computação"
            },
        ])

    } catch(err) {
        console.log(err)
        res.status(400).send("Erro")
    }
})

server.post("/aluno", async (req, res) => {
    try {
        let {nome, sobrenome, matricula} = req.body
        const newUser = await db.one(
            "INSERT INTO aluno (nome, sobrenome, matricula, nome_completo) VALUES ($1, $2, $3, $4);",
        [nome, sobrenome, matricula, nome + " " + sobrenome])
        res.status(200).json({nome, sobrenome, matricula})

    } catch(err) {
        console.log(err)
        res.status(400).send("Erro")
    }
})


server.get("/estoque", async (req, res) => {
    try {
        const estoque = await db.many("SELECT * FROM estoque;")
        res.status(200).json(estoque)

    } catch(err) {
        console.log(err)
        res.status(400).send("Erro")
    }
})

server.post("/estoque", async (req, res) => {
    try {
        let {descricao, quantidade, valor} = req.body
        const newProd = await db.none(
            "INSERT INTO estoque (descricao, quantidade, valor) VALUES ($1, $2, $3);",
        [descricao, parseInt(quantidade), parseFloat(valor)])

        res.status(200).json({descricao, quantidade, valor, valorTotal: valor * quantidade})

    } catch(err) {
        console.log(err)
        res.status(400).send("Erro")
    }
})



server.listen(PORT, () => console.log(`Server listening on port ${PORT}`))
