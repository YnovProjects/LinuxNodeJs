var express = require('express');
var router = express.Router();

var datas = require('../controllers/Datas');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/cpu-heat', datas.getCpuHeatInfos);
router.get('/cpu-freq', datas.getCpuFreqInfos);
router.get('/storage', datas.getStorageInfos);

router.get('/add/:socket', datas.addDatas);

module.exports = router;