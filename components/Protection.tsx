import React from 'react'
import { ProtectionOptions } from '@/constants';

interface ProtectionProps {
  onBack: () => void;
}

const ProtectionCard = ({ title, description, price }: Options) => {
  return (
    <div className="border border-gray-400 p-4 bg-white flex flex-col justify-between h-full">
      <div>
        <div className="flex items-center mb-2">
          <h3 className="text-lg font-bold">{title}</h3>
        </div>
        <p className="text-gray-600 mb-4">{description}</p>
      </div>
      <div className="mt-4 p-3 bg-blue-500 flex items-center justify-start">
        <input type="checkbox" className="form-checkbox text-red-500" />
        <span className="text-white font-bold pl-3">{price}</span>
      </div>
    </div>
  )
}

const Protection = ({ onBack }: ProtectionProps) => {
  return (
    <div className="container mx-auto p-4">
      <div className="container mx-auto flex items-center justify-between px-8">
        <h2 className="text-xl font-bold">Protection & Coverages</h2>
        <button
          onClick={onBack}
          className="border border-blue-500 text-blue-500 py-2 px-4 rounded"
        >
          BACK
        </button>
      </div>
      <div className="pt-6 grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-4">
        {ProtectionOptions.map((option) => (
          <ProtectionCard key={option.title} {...option} />
        ))}
      </div>
    </div>
  )
}

export default Protection

// <div className="border p-4 rounded flex flex-col justify-between">
//       <div>
//         <div className="flex items-center mb-2">
//           <h3 className="text-lg font-bold">{title}</h3>
//         </div>
//         <p className="text-gray-600">{description}</p>
//       </div>
//       <div className="mt-4 flex items-center justify-between">
//         <span className="text-red-500 font-bold">{price}</span>
//         <input type="checkbox" className="form-checkbox text-red-500" />
//       </div>
//     </div>