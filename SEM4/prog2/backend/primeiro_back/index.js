import express from 'express'
// import router from "./routes"

const server = express()
const PORT = 3000

server.use(express.json())
// server.use(router)


server.post("/soma", (req, res) => {
    let response = req.body
    res.status(200).send(`A soma é : ${response.a + response.b}`)
})


server.post("/strPar", (req, res) => {
    let request = req.body.text
    let response = ""
    for (let i = 0; i < response.length; i++) {
        if (i % 2 == 0) response += request[i]
    }
    console.log(response)
    res.status(200).send(response)
})

server.listen(PORT, () => console.log(`Server listening on port ${PORT}`))
