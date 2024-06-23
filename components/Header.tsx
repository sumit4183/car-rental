import Link from 'next/link';

const Header = () => {
  const isLoggedIn = false;

  return (
    <header className="theme-color p-3">
      <div className="container flex mx-auto items-center justify-between">
        <div className="flex items-center">
          <span className="text-2xl ml-3 font-semibold">
            EasyDrive
          </span>
        </div>
        <nav>
          {isLoggedIn ? (
            <Link href="/profile" className="mr-4"> Profile </Link>
          ): (
            <Link href="/sign-in" className="mr-4"> Sign-In/Sign-Up </Link>
          )}
        </nav>
      </div>
    </header>
  );
};

export default Header;
