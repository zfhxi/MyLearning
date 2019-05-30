from nose.tools import *
from ex49 import parser


def test_peek():
    test1 = [('stop', 'the'), ('noun', 'door')]
    result = parser.peek(test1)
    assert_equal(result, 'stop')

def test_match():
    test1 = [('stop', 'the'), ('noun', 'door')]
    result = parser.match(test1, 'stop')
    assert_equal(result, ('stop', 'the'))

def test_skip():
    test1 = [('direction', 'north'), ('noun', 'door')]  
    result = parser.skip(test1, 'direction')
    #assert_equal(result, ('direction', 'north'))
    assert_equal(result,None)


def test_parse_verb():
    test1 = [('stop', 'the'), ('verb', 'go'), ('noun', 'door')] 

    result = parser.parse_verb(test1)
    assert_equal(result, ('verb', 'go'))

    assert_raises(parser.ParserError, parser.parse_verb, test1)


def test_parse_object():
    test1 = [('stop', 'the'),('noun', 'door'), ('direction', 'north'),('verb', 'go') ]  

    result = parser.parse_object(test1)
    assert_equal(result, ('noun', 'door'))

    result = parser.parse_object(test1)
    assert_equal(result, ('direction', 'north'))

    assert_raises(parser.ParserError, parser.parse_object, test1)


def test_parse_subject():
    test1 = [('stop', 'the'),('verb', 'go'), ('noun', 'door')]  

    result = parser.parse_subject(test1, ('noun', 'wswsr'))
    assert_equal(result.subject, 'wswsr')
    assert_equal(result.verb, 'go')
    assert_equal(result.object, 'door')

def test_parse_sentence():
    test1 = [('stop', 'the'), ('noun', 'door'), ('verb', 'go'), ('noun', 'bear')]   

    result = parser.parse_sentence(test1)
    assert_equal(result.subject, 'door')
    assert_equal(result.verb, 'go')
    assert_equal(result.object, 'bear')

    test2 = [('stop', 'the'), ('verb', 'go'), ('noun', 'bear')] 

    result = parser.parse_sentence(test2)
    assert_equal(result.subject, 'player')
    assert_equal(result.verb, 'go')
    assert_equal(result.object, 'bear')

    test3 = [('direction', 'north'), ('noun', 'bear')]  

    assert_raises(parser.ParserError, parser.parse_sentence, test3)
