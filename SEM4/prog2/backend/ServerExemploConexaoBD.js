const express = require("express"); // Importa a biblioteca Express para criar o servidor
const cors = require("cors"); // Importa o middleware CORS para habilitar requisições de diferentes origens
const pgp = require("pg-promise")({}); // Importa a biblioteca pg-promise para interagir com o PostgreSQL


// Criação de uma instância do aplicativo Express
const app = express();
app.use(cors()); 
app.use(express.json()); 
app.listen(3010, () => console.log("Servidor rodando na porta 3010."));

// Configura a conexão com o banco de dados PostgreSQL
const usuario = "XXXXX"; 
const senha = "XXXXX";
const db = pgp(`postgres://${usuario}:${senha}@<Endereço do servidor>:<porta>/<nome da base>`);

// Rotas para /
app.get("/", (req, res) => {
    res.send("Hello, world!"); // Envia uma resposta de texto ao cliente
});


// Comentários sobre os métodos de consulta ao banco de dados
// db.any - 0 ou mais resultados
// db.all - retorna 1 ou mais resultados (PS. Funciona com sqlite3, no pg-promise usa-se db.any)
// db.one - apenas 1 resultado (Causa erro se a consulta retornar mais de um elemento)
// db.none - não retorna resultado - usado para atualizações

// Rota para obter todos os clientes
app.get("/clientes", async (req, res) => {
    try {
        // Faz a consulta ao banco de dados para obter todos os registros da tabela 'cliente'
        // Await pausa a execução do código até receber o retorno da consulta
        const clientes = await db.any("SELECT * FROM cliente;");
        console.log('Retornando todos cliente.'); 
        res.json(clientes).status(200); // Envia a lista de clientes em formato JSON com status 200
    } catch (error) {
        console.log(error); // Log do erro para depuração
        res.sendStatus(400); // Retorna status 400 em caso de erro
    }
});

// ROTA para obter um cliente específico
// Ex: http://localhost:3010/cliente?id=7
app.get("/cliente", async (req, res) => {
    try {
        const clienteId = parseInt(req.query.id); 
        console.log(`Retornando ID: ${clienteId}.`); 
        // Faz a consulta ao banco de dados para obter o cliente correspondente ao ID
        const clientes = await db.one(
            "SELECT id, nome, email FROM cliente WHERE id = $1;",
            clienteId
        );
        res.json(clientes).status(200); // Envia o cliente em formato JSON com status 200
    } catch (error) {
        console.log(error); // Log do erro para depuração
        res.sendStatus(400); // Retorna status 400 em caso de erro
    }
});

// ROTA para criar um novo cliente
app.post("/cliente", async (req, res) => {
    try {
        const clienteNome = req.body.nome; 
        const clienteEmail = req.body.email;
        console.log(`Nome: ${clienteNome} - Email: ${clienteEmail}`); 
        // Insere um novo cliente na tabela 'cliente' no banco de dados
        await db.none(
            "INSERT INTO cliente (nome, email) VALUES ($1, $2);",
            [clienteNome, clienteEmail]
        );
        res.sendStatus(200); // Retorna status 200 em caso de sucesso
    } catch (error) {
        console.log(error); // Log do erro para depuração
        res.sendStatus(400); // Retorna status 400 em caso de erro
    }
});
