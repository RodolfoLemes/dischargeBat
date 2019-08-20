const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const fs = require('fs')

const BATTERY = 0
const PORTA = 'COM6'

const port = new SerialPort(PORTA, { baudRate: 9600 })
const parser = port.pipe(new Readline({ delimiter: '\n' }))

// Read the port data
port.on('open', () => console.log("Serial port open"))

parser.on('data', data => {
    let dados = splitString(data)

    if(dados.voltage < 2.7){
        const context = data
        fs.writeFileSync(`./charge/${BATTERY}.txt}`, context, { flag:'a+' })
    } 
})


function splitString(data) {
    let string = data.split(' ')
    let voltage = string[1]
    let current = string[3]
    let capacity = string[5]
    let time = string[9]

    voltage = parseFloat(voltage.replace('V', null))
    current = parseFloat(current.replace('A', null))
    capacity = parseFloat(capacity.replace('Ah', null))
    time = parseFloat(time.replace('s', null))

    let dados = {
        voltage,
        current,
        capacity,
        time
    }

    return dados
}