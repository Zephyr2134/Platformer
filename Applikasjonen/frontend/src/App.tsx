import { useEffect } from 'react';
import './index.css';

const App = () => {

  useEffect(()=>{
    const script = document.createElement("script");
    script.src = "game.js";
    script.async = true;
    document.body.appendChild(script);
  }, []);

  return (
    <>
      <h1 className="text-red-600">The start</h1>
      <div className="relative p-[10px] w-[100%] flex flex-wrap justify-center">
      <canvas id="canvas" className="rounded-2xl" width="1200" height="550"></canvas>
      </div>
    </>
  )
}

export default App
