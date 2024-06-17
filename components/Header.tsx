import Link from 'next/link';
import Image from 'next/image';

const Header = () => {
  const isLoggedIn = false;

  return (
    <header className="theme-color p-3">
      <div className="container flex mx-auto items-center justify-between">
        <div className="flex items-center">
          {/* <Image
            src="/icons/logo.svg"
            height={40}
            width={40}
            alt="Company Logo"
            className="rounded-full"
          /> */}
          <span className="text-2xl ml-3 font-semibold">
            EasyDrive
          </span>
        </div>
        <nav>
          <Link href="" className="mr-4"> Home </Link>
          <Link href="/cars" className="mr-4"> Cars </Link>
          <Link href="/support" className="mr-4"> Support </Link>
          <Link href="/manage" className="mr-4"> Manage Rental </Link>
        </nav>
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
