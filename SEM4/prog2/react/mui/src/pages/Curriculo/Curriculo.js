import React from 'react';
import { Container, Typography, Box, Paper, Avatar } from '@mui/material';
import Grid from '@mui/material/Grid2';
import image from "../../assets/img/header_image.jpg"
import InformationTable from '../../components/InformationsTable';

function SectionTitle({message}) {
  return (
    <Typography component={"h2"} variant="h5" gutterBottom fontWeight="bold">{message}</Typography>
  )
}


const Curriculo = () => {
  return (
    <Container maxWidth="md">
      {/* Cabeçalho com Nome e Imagem */}
      <Box sx={{my: 4, display: 'flex', justifyContent: "center"}}>
        <Grid container alignItems="center" spacing={2}>
          <Grid item mr={4}>
            <Avatar
              alt="João Silva"
              src={image} 
              sx={{ width: 150, height: 150 }} 
            />
          </Grid>

          <Grid item spacing={0}>
            <Typography variant="h3" component="h1">
              Eduardo Fiorentin
            </Typography>
            <Typography variant="h5" color="textSecondary" component="h2" align='center'>
              Desenvolvedor de qualquer coisa 
            </Typography>
          </Grid>
          
        </Grid>
      </Box>

      {/* Sobre Mim */}
      <Box my={4}>
        <SectionTitle message={"Sobre mim"}/>
        <Typography variant="body1" sx={{fontSize: 18}}>
          Sou um desenvolvedor full stack com 5 anos de experiência em desenvolvimento de software. Especialista em
          React.js, Node.js e tecnologias de backend.
        </Typography>
      </Box>

      {/* Tabela de informações */}
      <SectionTitle message="Informações"/>
      <InformationTable/>

      {/* Experiência Profissional */}
      {/* <Box my={4}>
        <Typography variant="h6" component="h2" gutterBottom>
          Experiência Profissional
        </Typography>
        <Grid container spacing={3}>
          <Grid item xs={12} sm={6}>
            <Paper elevation={3} style={{ padding: 16 }}>
              <Typography variant="h6">Empresa ABC</Typography>
              <Typography variant="body2" color="textSecondary">
                2020 - Presente
              </Typography>
              <Typography variant="body1">Desenvolvedor Full Stack</Typography>
              <Typography variant="body2">
                Desenvolvimento de aplicações web utilizando React.js, Node.js e MongoDB.
              </Typography>
            </Paper>
          </Grid>
          <Grid item xs={12} sm={6}>
            <Paper elevation={3} style={{ padding: 16 }}>
              <Typography variant="h6">Empresa XYZ</Typography>
              <Typography variant="body2" color="textSecondary">
                2018 - 2020
              </Typography>
              <Typography variant="body1">Desenvolvedor Front-end</Typography>
              <Typography variant="body2">
                Desenvolvimento de interfaces responsivas utilizando React.js e Material-UI.
              </Typography>
            </Paper>
          </Grid>
        </Grid>
      </Box> */}

      {/* Educação */}
      {/* <Box my={4}>
        <Typography variant="h6" component="h2" gutterBottom>
          Educação
        </Typography>
        <ul>
          <li>Bacharelado em Ciência da Computação - Universidade Federal (2014-2018)</li>
          <li>Curso de React.js - Plataforma Udemy (2019)</li>
        </ul>
      </Box> */}
    </Container>
  );
};

export default Curriculo;
