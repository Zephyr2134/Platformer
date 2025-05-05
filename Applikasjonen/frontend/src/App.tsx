import { useState, useEffect } from "react";
import "./index.css";

const BASE_URL = "https://localhost:7071";

declare global {
  interface Window {
    dispatchReactEvent?: (eventname: string) => void;
  }
}

const App = () => {
  const [score, setScore] = useState(0);
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [loggedIn, setLoggedIn] = useState(false);

  const login = async () =>
  {
    if(username && password)
    {
      const response = await fetch(`${BASE_URL}/Game`, {
        method:"POST",
        headers:{"Content-Type":"application/json"},
        body: JSON.stringify({
          Username: username,
          Password: password
        })
      });
      if(response.ok)
      {
        setLoggedIn(true);
        const script = document.createElement("script");
        script.src = "game.js";
        script.async = true;
        document.body.appendChild(script);
      }
      setUsername("");
      setPassword("");
    }
  }

  useEffect(() => {
    

    (window as Window).dispatchReactEvent = (eventname: string) => {
      if (eventname == "GotCoin") {
        setScore((s) => s + 1);
      } else if (eventname == "ResetScore") {
        setScore(0);
      }
    };
  }, []);

  return (

    <>
    {loggedIn? 
    <div>
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
      <button onClick={(e)=>login()}>Login {loggedIn && <h1>LoggedIn</h1>}</button>
      </div>
: 
<>
  <div className="min-h-screen bg-gradient-to-b from-gray-900 via-gray-800 to-gray-900 flex flex-col items-center justify-start py-10 px-4">

    {/* Login Form */}
    <div className="w-full max-w-md bg-white/5 backdrop-blur-sm border border-green-400/20 p-6 rounded-xl shadow-lg mb-8">
      <h2 className="text-2xl font-bold text-green-300 mb-4 text-center">Login</h2>
      <form
        onSubmit={e=>{e.preventDefault(); login()}}
        className="flex flex-col space-y-4"
      >
        <input
          type="text"
          placeholder="Username"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          className="px-4 py-2 rounded-lg bg-gray-800 text-green-200 placeholder-green-400 border border-green-500/30 focus:outline-none focus:ring-2 focus:ring-green-400"
        />
        <input
          type="password"
          placeholder="Password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          className="px-4 py-2 rounded-lg bg-gray-800 text-green-200 placeholder-green-400 border border-green-500/30 focus:outline-none focus:ring-2 focus:ring-green-400"
        />
        <button
          type="submit"
          className="bg-green-500 hover:bg-green-400 text-gray-900 font-bold py-2 rounded-lg transition-all shadow-md"
        >
          Log In
        </button>
      </form>
      {loggedIn && (
        <p className="mt-4 text-green-400 text-center font-semibold">You're logged in!</p>
      )}
    </div>
  </div>
</>
}
    </>
  );
};

export default App;