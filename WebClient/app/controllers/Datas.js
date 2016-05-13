require('../models/Data');

var mongoose = require('mongoose');
var Data = mongoose.model('Data');

var _ = require('lodash');

function trim(str) {
  return str.replace(/^\s+|\s+$/gm,'');
}

var Datas = {
  getCpuHeatInfos: function(req, res) {
    Data.find({data: 'cpu-heat'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var cpuHeatDatas = [];
      for (var i = 0; i < datas.length; i++) {
        cpuHeatDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(cpuHeatDatas), title: 'CPU Heat', subtitle: 'in degrees celsius'});
    });
  },
  
  getCpuFreqInfos: function(req, res) {
    Data.find({data: 'cpu-freq'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var cpuFreqDatas = [];
      for (var i = 0; i < datas.length; i++) {
        cpuFreqDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(cpuFreqDatas), title: 'CPU Frequency', subtitle: 'in megahertz'});
    });
  },
  
  getStorageInfos: function(req, res) {
    Data.find({data: 'storage'}, '-_id value createAt', function(err, datas) {
      if (err) throw err;
      var storageDatas = [];
      for (var i = 0; i < datas.length; i++) {
        storageDatas.push([datas[i].createAt, datas[i].value]);
      }
      res.render('datas/index', {datas: JSON.stringify(storageDatas), title: 'Storage Used', subtitle: 'in kilobyte'});
    });
  },
  
  getUptimeInfos: function(req, res) {
    Data.find({data: 'uptime'}, '-_id uptime', {limit: 1, sort: {createAt: -1}}, function(err, datas) {
      if (err) throw err;
      res.render('datas/uptime', {data: datas[0].uptime, title: 'Last Uptime'});
    });
  },
  
  addDatas: function(data) {
    var socket = data.toString();
    var socketClean = [];
    for (var i = 0; i < socket.length; i++) {
      if (socket[i] == '0' || socket[i] == '1' || socket[i] == '2' || socket[i] == '3' || socket[i] == '4' || socket[i] == '5' || socket[i] == '6' || socket[i] == '7' || socket[i] == '8' || socket[i] == '9' || socket[i] == ':') {
        socketClean.push(socket[i]);
      }
    }
    socket = socketClean.toString().replace(new RegExp(',', 'g'), '');
    
    // Create an array with different informations from the socket string
    var socketArray = _.split(socket, ':');
    
    // Calculating the average CPUs' heat (cpusHeatAv)
    var cpusHeat = socketArray[0].match(/.{1,2}/g);
    var cpusHeatAc = Number(cpusHeat[0]) + Number(cpusHeat[1]) + Number(cpusHeat[2]) + Number(cpusHeat[3]);
    var cpusHeatAv = Number(cpusHeatAc) / 4;
    
    // Stock informations from the socket array
    var cpuFreq = socketArray[1];
    var storageUsed = socketArray[5];
    var lastUptime = socketArray[2] + ':' + socketArray[3] +':' + socketArray[4];
    
    // Create new entries
    var addCpuHeat = new Data({
      data: 'cpu-heat',
      value: cpusHeatAv
    });
    var addCpuFreq = new Data({
      data: 'cpu-freq',
      value: cpuFreq
    });
    var addStorage = new Data({
      data: 'storage',
      value: storageUsed
    });
    var addUptime = new Data({
      data: 'uptime',
      uptime: lastUptime
    });
    
    // Save entries
    addCpuHeat.save(function(err) {
      if(err) throw err;
      console.log('New cpu heat value added.')
    });
    addCpuFreq.save(function(err) {
      if(err) throw err;
      console.log('New cpu frequency value added.')
    });
    addStorage.save(function(err) {
      if(err) throw err;
      console.log('New storage value added.')
    });
    addUptime.save(function(err) {
      if(err) throw err;
      console.log('New uptime value added.')
    });
  }
};

module.exports = Datas;