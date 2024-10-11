import { Box, Link, Table, TableBody, TableCell, TableContainer, TableHead, TableRow, Typography } from "@mui/material";
import Paper from '@mui/material/Paper';
import React from "react";

import { styled } from '@mui/material/styles';
import { tableCellClasses } from '@mui/material/TableCell';

const rows = [
    {key: "Endereço", value: "Chapecó, Brasil"},
    {key: "Escolaridade", value: "Ensino superior em andamento"},
    {key: "E-mail", value: "eduardofiorentin336@gmail.com"},
    {key: "Celular", value: "54 9 9996-7787"},
    {key: "Github", value: <Link href="https://github.com/EduardoFiorentin" underline="hover" target="_blank" fontWeight="bold">Clique Aqui</Link>},
    {key: "Site", value: <Link href="https://portifolio-eduardofiorentin.netlify.app/" underline="hover" target="_blank" fontWeight="bold">Clique Aqui</Link>}
]

const StyledTableCell = styled(TableCell)(({ theme }) => ({
  [`&.${tableCellClasses.head}`]: {
    backgroundColor: theme.palette.common.black,
    color: theme.palette.common.white,
    fontWeight: "bold",
    fontSize: 18
  },
  [`&.${tableCellClasses.body}`]: {
    fontSize: 14,
  },
}));

const StyledTableRow = styled(TableRow)(({ theme }) => ({
  '&:nth-of-type(odd)': {
    backgroundColor: theme.palette.action.hover,
  },
  // hide last border
  '&:last-child td, &:last-child th': {
    border: 0,
  },
}));


export default function InformationTable() {
    return (
        <Box>
            <TableContainer component={Paper}>
                <Table sx={{ minWidth: 650 }} aria-label="simple table">
                    <TableHead>
                    <StyledTableRow>
                        <StyledTableCell align="center">Informações</StyledTableCell>
                        <StyledTableCell align="center"></StyledTableCell>
                    </StyledTableRow>
                    </TableHead>
                    <TableBody>
                    {rows.map((row) => (
                        <StyledTableRow
                        key={row.key}
                        sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                        >
                            <StyledTableCell component="th" scope="row" align="center"> {row.key} </StyledTableCell>
                            <StyledTableCell align="center"> {row.value} </StyledTableCell>
                        </StyledTableRow>
                    ))}
                    </TableBody>
                </Table>
            </TableContainer>
        </Box>
    )
}