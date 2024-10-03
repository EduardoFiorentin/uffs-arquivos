import "./Footer.css"

export default function Footer({email}) {
    return (
        <footer className="footer">
            <p className="footer_email">email: {email}</p>
        </footer>
    )
}