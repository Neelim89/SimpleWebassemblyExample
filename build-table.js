let btnAdd = document.querySelector('button');
let table = document.querySelector('table');

let nameInput = document.querySelector('#name');
let ageInput = document.querySelector('#age');
let countryInput = document.querySelector('#country');

function addPerson(name, age, country)
{
    Module.ccall ('addPerson',
                   null,
                   ['string'],
                   ["Nowmi", "25", "USA"]);
}

btnAdd.addEventListener('click', () => {
    let name = nameInput.value;
    let age = ageInput.value;
    let country = countryInput.value;

    let template =
                `<tr>
                    <td>${name}</td>
                    <td>${age}</td>
                    <td>${country}</td>
                </tr>`;

    table.innerHTML += template;
});

addPerson('Nowmi', '25', 'USA');