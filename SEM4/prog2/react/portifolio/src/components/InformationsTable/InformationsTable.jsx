import "./InformationsTable.css"

export default function InformationsTable() {
    return (
        <table className="table">
            <thead>    
                <tr className="info_title">
                    <td className="info_item-title-1">Informações</td>
                    <td className="info_item-title-2"></td>
                </tr>
            </thead>
            <tbody>
                <tr className="info_items">
                    <td className="info_item info_name">Endereço</td>
                    <td className="info_item">Chapecó, Brasil</td>
                </tr>
                <tr className="info_items">
                    <td className="info_item info_name">Escolaridade</td>
                    <td className="info_item">Ensino superior em andamento - Ciência da Computação - UFFS - 4° período</td>
                </tr>
                <tr className="info_items">
                    <td className="info_item info_name">Email</td>
                    <td className="info_item">eduardoviniciusfiorentin@gmail.com</td>
                </tr>
                <tr className="info_items">
                    <td className="info_item info_name">Celular</td>
                    <td className="info_item">(54) 99996-7764</td>
                </tr>
                <tr className="info_items">
                    <td className="info_item info_name">Github</td>
                    <td className="info_item"><a href="https://github.com/EduardoFiorentin" target="_blank" className="link">Clique aqui</a></td>
                </tr>
                <tr className="info_items">
                    <td className="info_item info_name">Site</td>
                    <td className="info_item"><a href="https://portifolio-eduardofiorentin.netlify.app" target="_blank" className="link">Clique aqui</a></td>
                </tr>
            </tbody>
        </table>
    )
}