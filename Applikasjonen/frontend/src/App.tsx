import { useState, useEffect } from 'react';
import './index.css';

declare global{
  interface Window{
    dispatchReactEvent?: (eventname:string)=>void;
  }
}

const App = () => {

  const [score, setScore] = useState(0);

  useEffect(()=>{
    const script = document.createElement("script");
    script.src = "game.js";
    script.async = true;
    document.body.appendChild(script);

    (window as Window).dispatchReactEvent = (eventname: string) =>{
      if(eventname == "GotCoin")
      {
        setScore(s=>s+1);
      }
    }
  }, []);

  return (
    <>
      <div className="min-h-screen bg-gradient-to-b from-gray-900 via-gray-800 to-gray-900 flex flex-col items-center justify-start py-10 px-4">
  <h1 className="text-4xl font-extrabold text-green-400 tracking-wider mb-6 neon-glow">
    SCORE: {score}
  </h1>

  <div className="relative p-4 w-full max-w-6xl rounded-xl border border-green-400/30 backdrop-blur-sm bg-white/5 shadow-xl">
    <canvas
      id="canvas"
      className="rounded-xl border border-green-500/20 shadow-lg"
      width="1200"
      height="550"
    ></canvas>
  </div>
</div>

    </>
  )
}

export default App
