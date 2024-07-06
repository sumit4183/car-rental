import { footerLinks } from "@/constants";

const Footer = () => {
    return (
      <footer className="bg-gray-800 text-white p-8">
        <div className="container mx-auto grid grid-cols-2 sm:grid-cols-3 lg:grid-cols-6 gap-8">
          {footerLinks.map((section) => (
            <div key={section.heading}>
              <h3 className="font-bold mb-2">{section.heading}</h3>
              <ul className="list-none">
                {section.links.map((link) => (
                  <li key={link.name} className="mb-1">
                    <a href={link.path} className="text-gray-400 hover:text-white">{link.name}</a>
                  </li>
                ))}
              </ul>
            </div>
          ))}
        </div>
        <div className="mt-8 text-center">
          <p>© 2024 EasyDrive. All rights reserved.</p>
        </div>
      </footer>
    );
  };
  
  export default Footer;
  