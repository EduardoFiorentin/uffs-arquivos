

class Database {

    constructor() {
        self.user = "progII"
        self.pass = "uffs"
        self.db = pgp(`postgres://${self.user}:${self.pass}@192.168.253.155:5432/progII`)
    }

    query(query, params) {
        const intem = self.db(query, params)
    }

}