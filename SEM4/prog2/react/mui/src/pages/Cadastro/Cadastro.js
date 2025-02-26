import { Box, Button, Input, TextField } from "@mui/material";
import { useEffect, useState } from "react";
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';

import { axios } from "../../services/axios/axios";


function createData(nome, matricula, curso) {
    return { nome, matricula, curso};
  }
  
//   const rows = [
//     createData('Frozen yoghurt', 159, 6.0, 24, 4.0),
//     createData('Ice cream sandwich', 237, 9.0, 37, 4.3),
//     createData('Eclair', 262, 16.0, 24, 6.0),
//     createData('Cupcake', 305, 3.7, 67, 4.3),
//     createData('Gingerbread', 356, 16.0, 49, 3.9),
//   ];
  



export function Cadastro() {

    const [nome, setNome] = useState()
    const [matricula, setMatricula] = useState()
    const [curso, setCurso] = useState()

    const [data, setData] = useState()
    const [rows, setRows] = useState([])

    async function handleSubmit() {
        try {

            if (nome && matricula && curso) {

                await axios.get("/aluno")
                .then(data => {
                    console.log(data.data)
                    handleSetData(data.data)
                })
                .catch((err) => {
                    console.log(err)
                })
                
            }

        } catch(err) {
            console.log(err)
        }
    }

    function handleSetData(data) {
        setData(data)
    }

    function buildRows() {
        let newRows = []

        if (data && data.length != 0) {
            for (let i = 0; i < data.length; i++) {
                console.log("row: ", data[i])
                newRows.push(createData(data[i].nome, data[i].matricula, data[i].curso))
            }
            setRows(newRows)
        }
        
    }

    useEffect(() => {
        buildRows()
    }, [data])

    return (
        <Box>
            <Box width={"400px"} margin={"auto"} mt={"50px"}>
                <Box display={"flex"} flexDirection={"column"} width={"400px"} gap={2}>
                    <TextField variant="outlined" label="Nome" value={nome} onChange={event => setNome(event.target.value)}/>
                    <TextField variant="outlined" label="Matricula" value={matricula} onChange={event => setMatricula(event.target.value)}/>
                    <TextField variant="outlined" label="Curso" value={curso} onChange={event => setCurso(event.target.value)}/>
                </Box>
                <Box display={"flex"} flexDirection={"column"} alignItems={"center"} gap={3} mt={"30px"}>
            
                    <Box display={"flex"} justifyContent={"center"} flexDirection={"column"} width={"250px"}>
                        <Button variant="contained" size="large" onClick={handleSubmit}>Cadastrar</Button>
                    </Box>
                    <Box display={"flex"} justifyContent={"center"} flexDirection={"column"} width={"250px"}>
                        <Button variant="outlined">Cancelar</Button>
                    </Box>
                </Box>
            </Box>
                {/* Renderização */}
            <Box width={"50%"} m="auto" mt="20px">
                <TableContainer component={Paper} width="300px">
                    <Table width="300px" aria-label="simple table">
                        <TableHead>
                        <TableRow>
                            <TableCell align="center" width={"100px"}>Nome</TableCell>
                            <TableCell align="center" width={"100px"}>Matricula</TableCell>
                            <TableCell align="center" width={"100px"}>Curso</TableCell>
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {rows.map((row) => (
                            <TableRow>
                                <TableCell align="center">
                                    {row.nome}
                                </TableCell>
                                <TableCell align="center">{row.matricula}</TableCell>
                                <TableCell align="center">{row.curso}</TableCell>
                            </TableRow>
                        ))}
                        </TableBody>
                    </Table>
                </TableContainer>
            </Box>
        </Box>
    )
}