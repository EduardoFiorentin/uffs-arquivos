import { useEffect, useRef, useState } from 'react'
import './App.css'

function App() {

  const [word, setWord] = useState("")

  const [focus, setFocus] = useState(false)
  const [timer, setTimer] = useState(0)
  const [start, setStart] = useState(false)
  const inputRef = useRef<HTMLInputElement>(null)

  useEffect(() => {

    if (start) {
      while (timer > 1) {
        setTimeout(() => setTimer(timer - 1), 1000)
      }
      setFocus(true)
      setTimer(30)
      while (timer > 1) {
        setTimeout(() => setTimer(timer - 1), 1000)
      }
      setStart(false)
    }

  }, [start])

  useEffect(() => {
    console.log("foco")
    if (inputRef.current && focus) {
      inputRef.current.focus();
      return;
    }

    if (inputRef.current) {
      inputRef.current.blur()
    }
  }, [focus]);

  
  const handleStart = () => {
    setTimer(5)
    setStart(true)
  }


  return (
    <>
     <h1 className='text-vermelho'>Hello, world</h1>
     <p>timer: {timer}</p>
     <p>text: {word}</p>
     <input type="text" name="" id="text" ref={inputRef} value={word} onChange={event => setWord(event.target.value)} autoFocus={false}/>
     <button onClick={() => handleStart()}>Começar</button>
    </>
  )
}

export default App
