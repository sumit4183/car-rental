import FeaturedCars from "@/components/FeaturedCars";
import Footer from "@/components/Footer";
import Header from "@/components/Header";

export default async function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  const loggedIn = true;

  return (
    <main>
      <Header />
      {children}
      <Footer />
    </main>
  );
}