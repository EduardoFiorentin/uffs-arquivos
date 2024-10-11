import express from "express"

export const router = express.Router()

router.get("/", (req, res) => {
    res.status(200).json(user)
})

router.post("/", (req, res) => {
    console.log(req.body)
    res.status(200).send("Lido...")
})

// module.exports = router