import React from 'react';

const PackageCard = ({ title, benefits, originalPrice, discountedPrice, savings }: PackageCardProps) => {
  return (
    <div className="border border-gray-400 bg-white p-4 flex flex-col justify-between h-full">
      <div>
        <div className="flex items-center justify-between mb-2">
          <h3 className="text-lg font-bold">{title}</h3>
          <span className="text-sm bg-black text-white px-2 py-1 rounded">{savings}</span>
        </div>
        <ul className="list-none mb-4">
          {benefits.map((benefit, index) => (
            <li key={index} className="text-gray-600 flex items-center">
              <span className="text-red-500 mr-2">✔</span> {/* Replace with actual icon */}
              {benefit}
            </li>
          ))}
        </ul>
      </div>
      <div className="mt-4 flex items-center justify-between">
        <div>
          <span className="text-gray-500 line-through mr-2">{originalPrice}</span>
          <span className="text-blue-500 font-bold">{discountedPrice}</span>
        </div>
        <input type="checkbox" className="form-checkbox text-red-500" />
      </div>
    </div>
  );
};

export default PackageCard;
