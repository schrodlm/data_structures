// add "type":"module" to your package.json!

import {faker as fakercz} from '@faker-js/faker/locale/cz';

const usedNames = new Map();
const usedNamesSet = new Set();

const rand = (size, errorPercentage) => [
    Math.floor(Math.random() * (size + size * (errorPercentage / 100))),
    Math.floor(Math.random() * (size + size * (errorPercentage / 100)))
]

const max = 50
for (let i = 0; i < max; i++)
{
    const name = fakercz.name.firstName();
    const random_val = fakercz.datatype.number(50);
    console.log(`T.insert_node("${name}", ${random_val});`);

    if (usedNames.has(name))
        console.log(`assert(T.find("${name}");`);
    else{
        usedNames[name] = random_val;
        usedNamesSet.add(name);

    }
    if (Math.random() < 0.33)
    {

        let names = Array.from(usedNamesSet);
        let random_toDel = names[Math.floor(Math.random() * names.length)];
        console.log(`T.delete_node("${random_toDel}", ${usedNames[random_toDel]});`);

        usedNames.delete(random_toDel);
        usedNamesSet.delete(random_toDel);


/*
        let keys = Array.from(usedNames.keys());
        let random_toDel = keys[Math.floor(Math.random() * keys.length)];
        console.log(`T.delete_node(${random_toDel});`);
*/

    }

}