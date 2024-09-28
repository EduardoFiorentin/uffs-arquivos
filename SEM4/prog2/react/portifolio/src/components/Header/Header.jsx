import "./Header.css"
import image from "../../assets/img/header_image.jpg"

export default function Header() {
    return (
        <header className="header">
        <div className="header_img-container">
            <img id="header_img-img" src={image} alt="Foto de eduardo fiorentin, a quem se referem as informações do curriculo"/>
        </div>
        <div className="header_text">
            <h1 className="header_title">Eduardo Fiorentin</h1>
            <p className="header_function">Desenvolvedor Front-End</p>
        </div>
    </header>
    )
}