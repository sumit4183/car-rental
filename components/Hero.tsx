import PromoMessage from "./PromoMessage";
import SearchBar from "./SearchBar";

const Hero = () => {
  const isLoggedIn = false;

  return (
    <div className="hero">
      <h2 className="hero-title">Find, book, rent a car—quick and super easy!</h2>
      <SearchBar />
      <PromoMessage />
    </div>
  );
};
  
  export default Hero;
  