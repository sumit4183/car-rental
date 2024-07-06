import Hero from "@/components/home/Hero";
import Link from "next/link";

export default function Home() {
  return ( 
    <div className="bg-cover bg-center bg-no-repeat" style={{ backgroundImage: "url('/photos/herobg.jpg')" }}>
      <div className="bg-black bg-opacity-50 p-8 rounded-md">
        <Hero />
      </div>
    </div>
  );
}
