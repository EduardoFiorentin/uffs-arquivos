import InformationsTable from "../InformationsTable/InformationsTable"
import "./Main.css"

export default function Main() {
    return (
        <main className="main">
            <section className="information">
                <h2 className="information-title title_item">Informações</h2>
                <div className="title-line"></div>
                
                <InformationsTable/>

            </section>

            <section className="education">
                <h2 className="education-title title_item">Escolaridade</h2>
                <div className="title-line"></div>

                <p className="information-item item">Graduação em <span style={{fontWeight: "bold"}}>Ciência da Computação</span> - 2022 a 2026</p>
                
            </section>

            <section className="objectives">
                <h2 className="objectives_title title_item">Objetivos</h2>
                <div className="title-line"></div>

                <ul>
                    <li><p className="objectives_item item">Desenvolvedor Front End Júnior</p></li>
                    <li><p className="objectives_item item">Estágio na área de TI</p></li>
                </ul>

            </section>
            
            <section className="skils">
                <h2 className="skills_title title_item">Habilidades</h2>
                <div className="title-line"></div>
                
                <h3 className="skills_hard subtitle_item">Hard Skills</h3>
                <p className="skills_item item">HTML | CSS | JavaScript | React | TypeScript | C++ | Python </p>
                <p className="skills_item item">React | TailWind | Bootstrap | Sass | TypeScript | Recoil | Express | Postgres | Git</p>
                <p className="skills_item item">Inglês Intermediario</p>
                
                <h3 className="skills_soft subtitle_item">Soft Skills</h3>
                <p className="skills_item item">Motivação | Trabalho em equipe | Organização e Gestão de tempo | Flexibilidade</p>
            </section>
        </main>
    )
}