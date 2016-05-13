var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var dateformat = require('dateformat');

var data = new Schema({
  data: {type: String, required: true},
  value: {type: Number, required: false},
  uptime: {type: String, required: false},
  createAt: {type: String, default: dateformat(Date(), 'yyyy/mm/dd HH:MM:ss')}
});

exports.model = mongoose.model('Data', data, 'datas');